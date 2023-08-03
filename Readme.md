# Specs for Windows 🪟:
## Installation:

It is a NodeJS module to get hardware informacions.

````
npm install specs_window
````

## Project info:
- author: Riseghost     👻
- languague:            C/C++
- platform support:     Windows 🪟
- github:               https://github.com/RiseGhost/specs_window
- npm profil:           https://www.npmjs.com/~riseghost

## Features:
- Get CPU Thread number;
- Get PC Name (Host Name);
- Get CPU Architecture ⚠️;
- Get Total RAM Memory install;
- Get Free RAM Memory;
- Get Available Drives (Units: C:\\, G:\\, F:\\, ...);
- Get Size Drives;
- Get Cursor/Mouse position;
- Move Cursor/Mouse;
- Get Screen Size


### Get CPU Threads number 🧠:

````JS
const specs = require('specs_window')

console.log(specs.getProcessorsNumber())
````

### Get PC Name (Host Name) 🖥️:

````JS
const specs = require('specs_window')

console.log(specs.getPCName())
````

### Get CPU Architecture ⚠️:
This func is under maintenance.
````JS
const specs = require('specs_window')

console.log(specs.getProcessorArchitecture())
````

### Get Total RAM Memory install 🗄️:

There are two func to get the Total Memory:
- getTotalMemory()
- getTotalMemoryGB()

##### getTotalMemory():

````JS
const specs = require('specs_window')

console.log(specs.getTotalMemory())
````

The fist func, getTotalMemory, return the following object:
````JS
{
  Bytes: 17041244160,
  KiloBytes: 16641840,
  MegaBytes: 16251.796875,
  GigaBytes: 15.870895385742188
}
````
##### getTotalMemoryGB():

````JS
const specs = require('specs_window')

console.log(specs.getTotalMemoryGB())
````

The second func, getTotalMemoryGB, return just GB:

````JS
15.870895385742188
````
### Get Free RAM Memory 🗄️🆓:

There are two func to get the Free Memory:
- getFreeMemory()
- getFreeMemoryGB()

##### getFreeMemory():

````JS
const specs = require('specs_window')

console.log(specs.getFreeMemory())
````

The first func, getFreeMemory, return the following object:

````JS
{
  Bytes: 3957870592,
  KiloBytes: 3865108,
  MegaBytes: 3774.51953125,
  GigaBytes: 3.686054229736328
}
````

#### getFreeMemoryGB():

````JS
const specs = require('specs_window')

console.log(specs.getFreeMemoryGB())
````

The second func, getFreeMemoryGB, return just GB:

````JS
3.686054229736328
````

### Get Available Drive ☑️💿:

This func return __all__ available drive path, include:
- Internal drives:
  - Hard disk;
  - SSD
- External drives:
  - pendrives;
  - external disk (HD or SSD)
  - ...

Does not work with smarphones, tables, nintendo switch, ... 

````JS
const specs = require('specs_window')

console.log(specs.getAvailableDrives())
````

````JS
[ 'C:\\', 'G:\\' ]
````

### Get Size Drives 🗄️💿:

This func return the Free Memory and Full Memory of Path Drive.

Path Dive is for exemple:
- C:\\\\
- G:\\\\
- F:\\\\
- ....

This func can you recive a individual Path Drive or a array with many Path Drive.

````JS
const specs = require('specs_window')

const Drives = specs.getAvailableDrives()

console.log(specs.getSizeDrives(Drives))
````

````JS
[
  { FreeMemory: 9531, FullMemory: 425668.99609375 },
  { FreeMemory: -1, FullMemory: -1 }
]
````

If the func can´t read a Memory of Drive return -1.

### Get Cursor/Mouse position 🐁🗺️:

Return the mouse position in the screen not in the window.

````JS
const specs = require('specs_window')

console.log(specs.getMousePos())
````

````JS
{ X: 1642, Y: 847 }
````

### Move Cursor/Mouse 🐁➡️:

Yes, you can move de Cursor/Mouse.

````JS
const specs = require('specs_window')

specs.MoveMouse(500,900)
````

### Get Screen Size 📺📐:

Return the Screen Size in pixeis.

````JS
const specs = require('specs_window')

console.log(specs.getScreenSize())
````

````JS
{ width: 1920, height: 1080 }
````
