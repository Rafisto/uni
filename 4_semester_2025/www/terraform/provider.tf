terraform {
    required_version = ">= 1.1.0"

    required_providers {
       proxmox = {
        source = "telmate/proxmox"
        version = "3.0.1-rc6"
       }
    }
}

provider "proxmox" {
    pm_api_url = var.proxmox_api_url
    pm_api_token_id = var.proxmox_api_token
    pm_api_token_secret = var.proxmox_api_password
}

variable "proxmox_api_url" {
    type = string
}

variable "proxmox_api_token" {
    type = string
    sensitive = true
}

variable "proxmox_api_password" {
    type = string
    sensitive = true
}
