const SerialPort = require('serialport')
const EventEmitter = require('events')

const Readline = SerialPort.parsers.Readline
const port = new SerialPort('/dev/ttyACM0')
const parser = new Readline({ delimiter: '\r\n' })
port.pipe(parser)

class IR extends EventEmitter {
  learn () {
    return new Promise((resolve, reject) => {
      // Switch to learning mode.
      port.write('learn\n')

      // Once we get data, learn from it.
      parser.once('data', (data) => {
        let x = new IRCommand(data)

        console.log(x)

        resolve(x)
        // Switch back to sending mode.
        port.write('send\n')
      })
    })
  }

  send (cmd) {
    const serialized = JSON.stringify(cmd, ['protocol', 'value', 'bits']) + '\n'
    console.log('Sending: ' + serialized)
    port.write(serialized)
  }
}

class IRCommand {
  constructor (protocol, value, bits) {
    if (arguments.length === 1) {
      // Actually the JSON object for the IRCommand.
      const obj = JSON.parse(protocol)

      this.protocol = obj.protocol
      this.value = obj.value
      this.bits = obj.bits
    } else {
      this.protocol = protocol
      this.value = value
      this.bits = bits
    }
  }
}

// Setup the Exports.
module.exports = new IR()

// Setup the events.
parser.on('data', function (data) {
  console.log(data)
  if (data === 'ready') {
    port.write('send\n')
    module.exports.emit('ready')
    return
  }

  module.exports.emit('data', data)
})
