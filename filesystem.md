- ext4文件系统详解：https://github.com/c-rainstorm/blog/blob/master/os/FileSystem-Ext4.md
- 自定义实现文件系统：https://www.write-bug.com/article/1360.html
- lru cache: 双端链表 实现
- 创建文件/目录的步骤：
  - 存储属性；文件属性的存储，内核先找到一块空的inode； 例如，内核找到i-节点号921130。内核把文件的信息记录其中。如文件的大小、文件所有者、和创建时间等。
  - 存储数据 即文件内容的存储，由于该文件需要3个数据块。因此内核从自由块的列表中找到3个自由块。如600、200、992，内核缓冲区的第一块数据复制到块600，第二和第三分别复制到922和600.
  - （目录过程） 找到空闲的数据块1002来存储目录的内容，只是目录的内容比较特殊，包含文件名字列表，列表一般包含两个部分：i-节点号和文件名，这个列表其实也就是文件的入口，新建的目录至少包含三个目录”.”和”..”其中”.”指向自己，”..”指向上级目录，我们可以通过比较对应的i-节点号来验证,887270 对应着上级目录中的child对应的i-节点号
  - 记录分配情况，数据保存到了三个数据块中。所以必须要记录起来，以后再找到正确的数据。分配情况记录在文件的i-节点中的磁盘序号列表里。这3个编号分别放在最开始的3个位置
  - 加文件名到目录，新文件的名字是userlist 内核将文件的入口(47,userlist)添加到目录文件里。文件名和i-节点号之间的对应关系将文件名和文件和文件的内容属性连接起来，找到文件名就找到文件的i-节点号，通过i-节点号就能找到文件的属性和内容。

文件系统如何存取文件的：
     1)、根据文件名，通过Directory里的对应关系，找到文件对应的Inodenumber
     2)、再根据Inodenumber读取到文件的Inodetable
     3)、再根据Inodetable中的Pointer读取到相应的Blocks
这里有一个重要的内容，就是Directory，他不是我们通常说的目录，而是一个列表，记录了一个文件/目录名称对应的Inodenumber。


### super_block

```c++
  // <include/linux/fs.h>
struct super_block{
  struct list_head s_list;    //指向超级块链表的指针
  dev_t  s_dev;               //设备标识符
  unsigned long s_blocksize;  //以字节为单位的块大小
  unsigned char s_blocksize_bits; //基本块设备驱动程序提到的以字节为单位的块大小
  unsigned char s_dirt;           //修改（脏）标志
  loff_t   s_maxbytes;            //文件的最大长度
  sturct file_system_type *s_type;  //文件系统类型
  const struct super_operations *s_op;  //超级块方法
  const struct dquot_operations *dp_op; //磁盘限额处理方法
  const struct quotactl_ops     *s_qcop;//磁盘限额管理方法
  const struct export_operations *s_export_op;  //网络文件系统使用的输出操作
  unsigned long s_flags;          //安装标志
  unsigned long s_magic;          //文件系统的magic words
  struct dentry *s_root;          //文件系统根目录的目录项对象
  struct rw_semaphore s_umount;   //卸载所用的信号量
  struct mutex s_lock;            //超级块信号量
  int s_count;                    //引用计数器
  int s_need_sync;                //对超级块的已安装文件系统进行同步的标志
  atomic_t s_active;              //次级引用计数器

  #ifdef CONFIG_SECURITY
    void *s_security;            //指向超级块安全数据结果的指针
  #endif

  struct xattr_handler **s_xattr; //指向超级块扩展属性结构的指针
  struct list_head s_inodes;      //所有索引节点的链表
  struct hllist_head s_anon;      //用于处理远程网络文件系统的目录项的链表
  struct list_head s_files;       //文件对象的链表
  struct list_head s_dentry_lru;  //
  int s_nr_dentry_unused;         //

  struct block_device *s_bdev;
  struct backing_dev_info *s_bdi;

  struct mtd_info *s_mtd;
  struct list_head s_instances;
  struct quota_info s_dquot;

  int s_frozen;
  wait_queue_head_t s_wait_unfrozen;

  char s_id[32];

  void *s_fs_info;
  fmode_t s_mode;
  struct mutex s_vfs_rename_mutex;
  u32 s_time_gran;
  char *s_subtype;
  char *s_options;
};
```


### inode（索引节点对象）
  索引节点是VFS中的核心概念，它包含内核在操作文件或目录时需要的全部信息。
  一个索引节点代表文件系统中的一个文件(这里的文件不仅是指我们平时所认为的普通的文件，还包括目录，特殊设备文件等等)。
  索引节点和超级块一样是实际存储在磁盘上的，当被应用程序访问到时才会在内存中创建。
  文件系统处理文件所需要的所有信息都存放在一个名为索引节点的数据结构中;
 ```c++
 <include/linux/fs.h>
 struct inode{
    struct hlist_node   i_hash;     //散列表的指针
    struct list_head    i_list;     //描述索引节点当前状态的链表指针
    struct list_head    i_sb_list;  //超级块的索引节点链表的指针
    struct list_head    i_dentry;   //引用索引节点的目录项对象链表的头
    unsigned long       i_ino;      //索引节点号
    atomic_t            i_count;    //引用计数器
    unsigned int        i_nlink;    //硬链接数目
    uid_t               i_uid;      //所有者标识符
    gid_t               i_gid;      //组标识符
    dev_t               i_rdev;     //实设备标识符
    u64                 i_version;  //版本号，每次使用之后自动递增
    loff_t              i_size;     //

#ifdef __NEED_I_SIZE_ORDERED
    seqcount_t          i_size_seqcount;  //SMP系统为i_size字段获取一致值时使用的顺序计数器
#endif
    struct timespec     i_atime;
    struct timespec     i_mtime;
    struct timespec     i_ctime;
    blkcnt_t            i_blocks;
    unsigned int        i_blkbits;
    unsigned short      i_bytes;
    umode_t             i_mode;
    spinlock_t          i_lock;
    struct mutex        i_mutex;
    struct rw_semaphore i_alloc_sem;
    const struct inode_operations *i_op;    /* 索引节点操作函数 */
    const struct file_operations  *i_fop;  //缺省的索引节点操作 */
    struct super_block  *i_sb;            //相关的超级块
    struct file_lock    *i_flock;
    struct address_space *i_mapping;      //相关的地址映射 
    struct address_space i_data;          //设备地址映射
 
 #ifdef CONFIG_QUOTA
    struct dquot        *i_dquot[MAXQUOTAS];
 #endif
    
    struct list_head    i_devices;
    union{
        struct pipe_inode_info *i_pipe;
        struct block_device    *i_bdev;
        struct cdev            *i_cdev;
    };
  
    __u32               i_generation;
    
  #ifdef CONFIG_FSNOTIFY
     __u32              i_fsnotify_mask;
     struct hlist_head  i_fsnotify_mark_entries;
  #endif
    
  #ifdef CONFIG_INOTIFY
      struct list_head inotify_watches;
      struct mutex     inotify_mutex;
  #endif
    
    unsigned long   i_state;
    unsigned long   dirtied_when;
    unsigned int    i_flags;
    atomic_t        i_writecount;
    
 #ifdef CONFIG_SECURITY
    void *i_security;
 #endif
 
 #ifdef CONFIG_FS_POSIX_ACL
    struct posix_acl  *i_acl;
    struct posix_acl  *i_default_acl;
 #endif
    void *i_private;
 };
 
 struct inode_operations{
    //为dentry对象创建一个新的索引节点
    int (*create)(struct inode*, struct dentry *, int, struct nameidata *);
    //在特定文件夹中寻找索引节点，该索引节点要对应于dentry中给出的文件名
    struct dentry *(*lookup) (struct inode*, struct dentry*, struct nameidata*);
    //创建硬链接
    int (*link)(struct dentry*, struct inode*, struct dentry*);
    
    //从一个符号链接查找它指向的索引节点
    void * (*fllow_link) (struct dentry *, struct nameidata*);
    
    //在follow_link调用之后，该函数由VFS调用进行清除工作
    void (*put_link) (struct dentry*, struct nameidata *, void *);
    
    //该函数由VFS调用，用于修改文件的大小
    void (*truncate) (struct inode*);
 };
 ```
每个索引节点（inode）对象都会复制磁盘索引节点包含的一些数据，比如分配给文件的磁盘块数。如果i_state字段的值等于I_DIRTY_SYNC、I_DIRTY_DATASYNC或I_DIRTY_PAGES，该索引节点就是『脏』的，也就是说，对应的磁盘索引节点必须被更新。

http://guojing.me/linux-kernel-architecture/posts/super-block-object/


### 目录项
  和超级块和索引节点不同，目录项并不是实际存在于磁盘上的。
  在使用的时候在内存中创建目录项对象，其实通过索引节点已经可以定位到指定的文件，
  但是索引节点对象的属性非常多，在查找，比较文件时，直接用索引节点效率不高，所以引入了目录项的概念
  
  路径中的每个部分都是一个目录项，比如路径： /mnt/cdrom/foo/bar 其中包含5个目录项，/ mnt cdrom foo bar
  
  每个目录项对象都有3种状态：被使用，未使用和负状态
    - 被使用：对应一个有效的索引节点，并且该对象由一个或多个使用者
    - 未使用：对应一个有效的索引节点，但是VFS当前并没有使用这个目录项
    - 负状态：没有对应的有效索引节点（可能索引节点被删除或者路径不存在了）
目录项的目的就是提高文件查找，比较的效率，所以访问过的目录项都会缓存在slab中。
slab中缓存的名称一般就是 dentry(目录项对象结构)，可以通过如下命令查看：

### 内核访问块设备的方法
  内核通过文件系统访问块设备时，需要先把块读入到内存中，所以文件系统为了管理块设备，必须管理块和内存页之间的映射;
  内核中有两种方法来管理块和内存页之间的映射：
    - 缓冲区和缓冲区头
    - bio
#### 缓冲区和缓冲区头
  每个 [块] 都是一个缓冲区，同时对每个 [块] 都定义一个缓冲区头来描述它。
  由于 [块] 的大小是小于内存页的大小的，所以每个内存页会包含一个或者多个 [块]。
```c++
//<linux/buffer_head.h>: include/linux/buffer_head.h
struct buffer_head{
  unsigned long b_state;
  struct buffer_head *b_this_page; 
  struct page *b_page;
  
  sector_t b_blocknr;
  size_t b_size;
  char *b_data;
  
  struct block_device *b_bdev;
  bh_end_io_t *b_end_io;
  void *b_private;
  struct list_head b_assoc_buffers;
  struct address_space *b_assoc_map;
  atomic_t b_count;
};
```
在2.6之前的内核中，主要就是通过缓冲区头来管理 [块] 和内存之间的映射的。

用缓冲区头来管理内核的 I/O 操作主要存在以下2个弊端，所以在2.6开始的内核中，缓冲区头的作用大大降低了。
- 弊端 1
  对内核而言，操作内存页是最为简便和高效的，所以如果通过缓冲区头来操作的话（缓冲区 即[块]在内存中映射，可能比页面要小），效率低下。
而且每个 [块] 对应一个缓冲区头的话，导致内存的利用率降低（缓冲区头包含的字段非常多）
- 弊端 2
  每个缓冲区头只能表示一个 [块]，所以内核在处理大数据时，会分解为对一个个小的 [块] 的操作，造成不必要的负担和空间浪费。
 
#### bio
  bio结构体的出现就是为了改善上面缓冲区头的2个弊端，它表示了一次 I/O 操作所涉及到的所有内存页。
```c++
/*
 * I/O 操作的主要单元，针对 I/O块和更低级的层 (ie drivers and
 * stacking drivers)
 */
struct bio {
    sector_t        bi_sector;    /* 磁盘上相关扇区 */
    struct bio        *bi_next;    /* 请求列表 */
    struct block_device    *bi_bdev; /* 相关的块设备 */
    unsigned long        bi_flags;    /* 状态和命令标志 */
    unsigned long        bi_rw;        /* 读还是写 */

    unsigned short        bi_vcnt;    /* bio_vecs的数目 */
    unsigned short        bi_idx;        /* bio_io_vect的当前索引 */

    /* Number of segments in this BIO after
     * physical address coalescing is performed.
     * 结合后的片段数目
     */
    unsigned int        bi_phys_segments;

    unsigned int        bi_size;    /* 剩余 I/O 计数 */

    /*
     * To keep track of the max segment size, we account for the
     * sizes of the first and last mergeable segments in this bio.
     * 第一个和最后一个可合并的段的大小
     */
    unsigned int        bi_seg_front_size;
    unsigned int        bi_seg_back_size;

    unsigned int        bi_max_vecs;    /* bio_vecs数目上限 */
    unsigned int        bi_comp_cpu;    /* 结束CPU */

    atomic_t        bi_cnt;        /* 使用计数 */
    struct bio_vec        *bi_io_vec;    /* bio_vec 链表 */
    bio_end_io_t        *bi_end_io; /* I/O 完成方法 */
    void            *bi_private;    /* bio结构体创建者的私有方法 */
#if defined(CONFIG_BLK_DEV_INTEGRITY)
    struct bio_integrity_payload *bi_integrity;  /* data integrity */
#endif
    bio_destructor_t    *bi_destructor;    /* bio撤销方法 */
    /*
     * We can inline a number of vecs at the end of the bio, to avoid
     * double allocations for a small number of bio_vecs. This member
     * MUST obviously be kept at the very end of the bio.
     * 内嵌在结构体末尾的 bio 向量，主要为了防止出现二次申请少量的 bio_vecs
     */
    struct bio_vec        bi_inline_vecs[0];
};
```
```c++
struct request{
  struct list_head queulist;
  struct call_single_data csd;
  
  struct request_queue *q;
  unsigned int cmd_flags;
  
  enum rq_cmd_type_bits cmd_type;
  unsigned long atomic_flags;
};
```
谓的合并指的是该bio所请求的io是否与当前已有request在物理磁盘块上连续，如果是，无需分配新的request，直接将该请求添加至已有request，
这样一次便可传输更多数据，提升IO效率，这其实也是整个IO系统的核心所在。

linux下如何实现文件一致性：
  - 提供特定接口(fsync,fdatasync, sync),调用接口来主动保证文件系统一致性;
  - 系统中存在定期任务（表现形式为内核线程，周期性地同步文件系统中文件脏数据块;
  
这两种方式互相补充，方式1可保证文件数据的强一致性，但效率较为低下，每次写入必须等待数据写入磁盘方可返回，方式2克服了1的低效，
但无法保证文件数据的always consistent。
  
//IO系统磁盘调度子系统的ftrace跟踪，blktrace跟踪事件;
  - 请求相关
    Q - queued：bio请求进入调度
    G - get request 分配request
    I - inserted request进入io调动器
  
  - 调动相关  
      B - bounced：硬件无法访问内存，需要把内存降低到硬件可访问
      M - back merge： request 和前一个request从后面合并
      F - front merge： request 和前一个request从前面合并
      X - split： request分析为多个子request
      A - remap： 基于分区等，重新映射request的位置
      R - requeue： request重新回到调度队列
      S - sleep： 调度器进入休眠
      P - plug： 调动队列插入设备（准备合并）
      U - unplug： 调度队列离开设备
      T - unplug due to timer 超时，

  - 发出相关
    C - complete：完成一个request的调度（无论成功还是失败）
    D - issued：发送到设备，这个是从下层硬件驱动发起的   
      
      
      
      
       
      

https://zhuanlan.zhihu.com/p/44608189
https://blog.csdn.net/joker0910/article/details/8250085 //Radix树在Linux中的应用
https://www.cnblogs.com/huangxincheng/archive/2012/11/25/2788268.html //trie树 
