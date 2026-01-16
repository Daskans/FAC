# Etude d’un réseau existant

### 1 Présentation de QEMU

lancer qemu
```cmd
cd /net/stockage/aguermou/AR/TP/1/; ./qemunet.sh -x -t topology -a archive_tp1.tgz
```

```cmd
ip addr add 172.16.0.1/24 dev eth0
```

```cmd
nano /etc/network/interfaces
```

`auto eth0
iface eth0 inet static
address 172.16.0.2/24`