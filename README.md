
<p align="center">
<img src="assets/" width="425" />
</p>
  
> **⚠ Warning**<br> This operating system is still under development. Wouldn't recommend you to use it yet. 

<br>

## Getting Started:

**1.** Build the OS:
```
$ git clone https://github.com/DrSoftman/VikingOS
$ cd VikingOS
$ make img
```


**2.** Run the OS with QEMU:
```
$  qemu-system-i386 --drive format=raw,file=vikingos.img -montior stdio -no-reboot -d guest_errors,int,pcall,unimp,out_asm -D debug.log
```
Remove the ``-monitor stdio`` and use ``-nographic`` to run it just in the terminal.

**Building on real hardware...**
Here is how to building it on real hardware. If you want your computer to sent to deepest depths of agony and suffering, then I would recommend you to use this method!
```
$ make iso
```
Burn the vikingos.iso onto a bootable USB, this might work or not.. Good luck!

## Support:
Please email me on kaenklalle@gmail.com!
I will try to respond as soon as possible if I have time! God bless!
