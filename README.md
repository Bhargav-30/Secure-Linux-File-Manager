## 13. Kernel Driver Testing Note

The Linux character device driver is implemented as an external kernel module using the Linux kernel character-device APIs.

The driver successfully compiles against the Microsoft WSL 6.18.40.1 kernel source and produces the `slf_audit.ko` module.

During runtime testing on the stock WSL kernel, module insertion was rejected with:

```text
.gnu.linkonce.this_module section size must match
the kernel's built struct module size at run time
