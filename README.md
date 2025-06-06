
<p align="center">
<img src="assets/VikingOS_git_logo.png" width="400" />
</p>
  
> **⚠ Warning**<br> VikingOS is still under development and lacks a lot of features. I do not recommend you to use it just yet.


## Getting Started:

**1.** Build the OS:
```
$ git clone https://github.com/Wickslynx/AuroraOS
$ cd AuroraOS
$ make img
```


**2.** Run the OS with QEMU:
```
$  qemu-system-i386 --drive format=raw,file=auroraos.img -monitor stdio -no-reboot -d guest_errors,int,pcall,unimp,out_asm -D debug.log
```
Remove the ``-monitor stdio`` and use ``-nographic`` to run it just in the terminal.

**Building on real hardware...**
So you are building AuroraOS on real hardware, I wouldn't recommend it but here is how.
```
$ make iso
```
Burn the auroraos.iso onto a bootable USB, this might work or not.. Good luck!

## Support:
Please email me on kaenklalle@gmail.com!
I will try to respond as soon as possible if I have time! God bless!
