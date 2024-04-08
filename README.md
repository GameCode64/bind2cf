# Bind to cloudflare service
This is a service to sync a local bind service up to the cloud dns service provider: CloudFlare
Like for example to run with virtualmin to request a wildcard certificate for your domain, which requires a CNAME validation.

---
# WORK IN PROGRESS
---

## Requirements
 - Ubuntu 22.04 + ( Redhat installation & configuration will be made after completion of the alpha phase)
 - make
 - Bind
 - Cloudflare account

## Installation
There is no official installation procedure yet, till the alpha phase

### Required files placement
```sh
mkdir -p /etc/bind2cf
cat << 'EOF' > /etc/bind2cf/conf.json
{
        "apikey":"## Cloudflare API key ##",
        "tmpfolder":"/tmp/bind2cf",
        "syncdirection": 0 ,
        "key": ""
}
EOF


cat << 'EOF' > /etc/bind2cf/mount.json
[
  {
    "domain": "## Domainname ##",
    "cloudflareID": "## CloudflareID of the zone ##",
    "bindfile": "## Path to the bindfile to link the zone ##"
  }
]
EOF

```

# Credits
The creators of certain projects I use in this project as libraries, deserves some credits for their work.

The following libraries are in {Projectfolder}/src/lib

 - Json engine: https://github.com/nlohmann/json
 - Restclient: https://github.com/mrtazz/restclient-cpp
 - QuickHelpers: Me (GameCode64/Ricky Visser)


