## MCUboot port example

This repo is an example of porting MCUboot to a new platform. Everything specific to the MCUboot port is in the folder `source/app/mcuboot_port`.

### Application development

To run with MCUboot, an application must fulfil the following requirements:

- Linked to start at the `APPLICATION_PRIMARY_START_ADDRESS` plus the image header size. Currently this is `0x08020000 + 0x200 = 0x08020200`.
- Image must be post-processed using `imgtool` to add header, trailer, and sign the image using `key.pem`.

An example of an application can be found in the `stm32_starter` repo.

Build the image in that repo and then use `make sign_app` to process and sign the image using `imgtool`.

If flashing the application directly into the primary slot, it should also be confirmed (`--confirm`) using `imgtool`.

Loading a confirmed image into the secondary slot is also possible, and means that it will be swapped permanently into the primary slot on the next boot without the application having to trigger the update.
