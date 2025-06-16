resource "proxmox_vm_qemu" "my_proxmox_vm" {
    for_each    = var.proxmox_vm
    name        = each.value.name
    desc        = each.value.hostname
    vmid        = each.value.vm_id
    target_node = each.value.target_node
    memory      = each.value.memory
    cores       = each.value.vcpu
    tags        = each.value.tags
    cpu         = "host"

    os_type     = "cloud-init"
    clone       = each.value.img_template
    full_clone  = true

    agent       = 1
    ciuser      = "wms"
    cipassword  = "wms"
    ciupgrade   = true

    sshkeys     = file("${var.ssh_key_public}")
    ipconfig0   = "${each.value.ipconfig0}"
    nameserver = "192.168.88.1 8.8.8.8"

    vm_state    = "running"

    scsihw = "virtio-scsi-single"
    boot = "order=scsi0"

    disks {
        scsi {
            scsi0 {
                disk {
                    storage  = "raid"
                    size     = each.value.boot_disk_size
                    iothread = each.value.boot_disk_iothread
                }
            }
        }
        ide {
            ide1 {
                cloudinit {
                    storage = "raid"
                }
            }
        }
    }

    serial {
        id   = 0
    }

    network {
        model      = "virtio"                 
        bridge     = each.value.vnic_bridge
    }

    tablet = false

    lifecycle {
        ignore_changes = [
            network
        ]
    }
}
