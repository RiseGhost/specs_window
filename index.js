const specs = require('./build/Release/specs_window');

class Pessoa{
    constructor (name, id){
        this.name = name;
        this.id = id;
    }
}

const p = new Pessoa("Jorge", 89);

console.log(specs.getProcessorsNumber())
console.log(specs.getPCName())
console.log(specs.getProcessorArchitecture())
console.log(specs.getTotalMemoryGB())
console.log(specs.getTotalMemory())
console.log(specs.getFreeMemoryGB())
console.log(specs.getFreeMemory())
console.log(specs.getAvailableDrives())
console.log(specs.getSizeDrives("Hoje"))
console.log(specs.getSizeDrives(["VV","DS","da"]))
console.log(specs.getSizeDrives([[34,6,5],[34,6,5]]))
console.log(specs.getSizeDrives(p))