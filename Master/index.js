const SerialPort = require('serialport')
const Readline = SerialPort.parsers.Readline

const port = new SerialPort('/dev/ttyACM0')

var parser = new Readline()
port.pipe(parser)
parser.on('data', function (data) {
  data = data.trim()
  console.log(data)
  if (data === 'ready') {
    port.write('Hello, World!\n')
  }
})
