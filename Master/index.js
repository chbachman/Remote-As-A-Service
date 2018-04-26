const express = require('express')
const app = express()

const ir = require('./ir')

ir.once('ready', () => {
  let command

  app.get('/learn', async (req, res) => {
    console.log('Learning!')
    command = await ir.learn()
    console.log('Learned!')
  })

  app.get('/send', (req, res) => {
    if (command) {
      console.log('Sending: ' + JSON.stringify(command))
      ir.send(command)
    }
  })

  app.listen(3000, () => {
    console.log('Example app listening on port 3000!')
  })
})
