const specs = require('./build/Release/specs_window');

module.exports = {
    getProcessorsNumber:        specs.getProcessorsNumber,
    getPCName:                  specs.getPCName,
    getProcessorArchitecture:   specs.getProcessorArchitecture,
    getTotalMemoryGB:           specs.getTotalMemoryGB,
    getTotalMemory:             specs.getTotalMemory,
    getFreeMemoryGB:            specs.getFreeMemoryGB,
    getFreeMemory:              specs.getFreeMemory,
    getAvailableDrives:         specs.getAvailableDrives,
    getSizeDrives:              specs.getSizeDrives,
    getMousePos:                specs.getMousePos,
    getScreenSize:              specs.getScreenSize
}