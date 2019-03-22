

```c++
// <include/linux/fs.h>
struct super_block{
  struct list_head s_list;  
  dev_t  s_dev;
  unsigned long s_blocksize;
  unsigned char s_blocksize_bits;
  unsigned char s_dirt;
  loff_t   s_maxbytes;
  sturct file_system_type *s_type;
  const struct super_operations *s_op;
  const struct dquot_operations *dp_op;
  const struct quotactl_ops     *s_qcop;
  const struct export_operations *s_export_op;
  unsigned long s_flags;
  unsigned long s_magic;
  struct dentry *s_root;
  struct rw_semaphore s_umount;
  struct mutex s_lock;
  int s_count;
  int s_need_sync;
  atomic_t s_active;

#ifdef CONFIG_SECURITY
  void *s_security;
#endif

  struct xattr_handler **s_xattr;
  struct list_head s_inodes;
  struct hllist_head s_anon;
  struct list_head s_files;
  struct list_head s_dentry_lru;
  int s_nr_dentry_unused;

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