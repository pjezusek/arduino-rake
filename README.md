# arduino-rake
Rake file that allows to build and upload arduino programs to board.
It uses arduino-cli to manage compilation an installation process.
It was prepared to work on Linux.

# Prerequirements
  * [arduino-cli](https://github.com/arduino/arduino-cli) (tested on 0.3.6-alpha.preview)
  * [proper arduino core](https://github.com/arduino/arduino-cli#step-4-find-and-install-the-right-core)
  * [rake](https://github.com/ruby/rake)
  * [stty](https://linux.die.net/man/1/stty) 
  * [screen](https://www.gnu.org/software/screen/) (optionally for serial communication)

# Configuration
You can configure this script using following variables:

  * **FQBN** - board name (default: arduino:avr:uno)
  * **BUILD_DIR** - directory for files created during building process (default: ./build)
  * **CACHE_DIR** - directory for caching (default: ./build/cache)
  * **DEV_TTY** - tty used for communication with board (default: /dev/ttyACM0)
  * **OUTPUT_FILE** - compilation process output file location/name (default: ./**BUILD_DIR**/output.hex)
  * **TTY_TARGET_PARAMS** - result of `stty -g /dev/<TTY>` which is used to check if tty is properly configured
  * **TTY_CONFIG_PARAMS** - params for `stty` that will be used to configure tty

# Use cases
Call commands using following pattern: `rake arduino:<command_name>`

### build
Compile project and create **BUILD_DIR** and **CACHE_DIR** if necessary

### upload
Upload project to board

### install
Build and upload project

### check_tty
Check if **DEV_TTY** is properly configured

### configure_tty
Configure **DEV_TTY** using `stty`

### run
Run screen session on **DEV_TTY**

# Template sketch
Repository includes simple sketch ready to testing board.
Just type `rake arduino:install` to build and upload program.
It turns on and turns off LED built into arduino. It can be used also to test serial connection.

**If you have any questions or suggestions, feel free to create an issue.**

