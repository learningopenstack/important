### linux io

```c++
                                    Application
        _____________________________________________________________
                           |       |           |     
               Buffered IO |       |mmap       | Direct IO  
                    File System    |           | 
                           |       |           | 
                           |       |           | 
                          page  Cache          | 
                               |               | 
                               Block   IO    Layer 
                                   |            | 
                                   Device & Disk etc...
 ```        
 传统的Buffered IO使用read(2)读取文件的过程什么样的？(假设cache中不存在)
    - open(2)打开文件内核后建立了一系列的数据结构
    - 调用read(2)，到达文件系统这一层，发现Page Cache中不存在该位置的磁盘映射
    - 然后创建相应的Page Cache并和相关的扇区关联
    - 后请求继续到达块设备层，在IO队列里排队，接受一系列的调度后到达设备驱动层，此时一般使用DMA方式读取相应的磁盘扇区到Cache中，
    然后read(2)拷贝数据到用户提供的用户态buffer中去（read(2)的参数指出的）。
    
  整个过程中有几次拷贝？ 
    - 从磁盘到Page cache 第一次
    - page cache到用户态buffer第二次
  
    mmap(2)做了什么？mmap(2)直接把Page Cache映射到了用户态的地址空间里了;所以mmap（2）的方式读文件是没有第二次拷贝过程的;
    Direct IO呢？这个机制更狠，直接让用户态和块IO层对接，直接放弃Page Cache，从磁盘直接和用户态拷贝数据。好处是什么？
    写操作直接映射进程的buffer到磁盘扇区，以DMA的方式传输数据，减少了原本需要到Page Cache层的一次拷贝，提升了写的效率。
    对于读而言，第一次肯定也是快于传统的方式的，但是之后的读就不如传统方式了（当然也可以在用户态自己做Cache，有些商用数据库就是这么做的）  
