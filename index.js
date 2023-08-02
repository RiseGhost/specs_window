const specs = require('./build/Release/specs_window');

console.log(specs.getProcessorsNumber())
console.log(specs.getPCName())
console.log(specs.getProcessorArchitecture())
console.log(specs.getTotalMemoryGB())
console.log(specs.getTotalMemory())
console.log(specs.getFreeMemoryGB())
console.log(specs.getFreeMemory())