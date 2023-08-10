const specs = require('./build/Release/specs_window');

async function get_Processes(){     return specs.GetProcesses() }
async function Kill_Processe(PID){  return specs.KillProcesse(PID) }
async function FilesPath(Path){  return specs.getFilesPath(Path) }

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
    getScreenSize:              specs.getScreenSize,
    MoveMouse:                  specs.MoveMouse,
    getProcesses:               get_Processes,
    KillProcesse:               Kill_Processe,
    getFilesPath:               FilesPath,
    getProcessorsCore:          specs.getProcessorsCore,
}