const express = require('express')
const shortid = require('shortid')
const Datastore = require('./db')
const ir = require('./ir')

const app = express()
const db = new Datastore({filename: '../Remote-Data/ir.db', autoload: true})

ir.once('ready', () => {
  app.use('/web', express.static('web'))

  app.get('/learn', async (req, res) => {
    const id = shortid.generate()
    const name = req.query.name

    res.send({
      id: id
    })

    console.log(`Learning: ${id}`)
    const command = await ir.learn()

    db.insert({
      _id: id,
      command: command,
      name: name
    })

    console.log(`Learned: ${id}`)
  })

  app.get('/list/:id', async (req, res) => {
    const id = req.params.id
    const command = await db.get(id)

    if (command) {
      res.send(command)
    } else {
      res.send()
    }
  })

  app.get('/list', async (req, res) => {
    const list = await db.list()
    res.send(list)
  })

  app.delete('/list/:id', async (req, res) => {
    const id = req.params.id

    console.log(`Deleting: ${id}`)

    await db.delete(id)

    res.sendStatus(200)
  })

  app.get('/send/:id', async (req, res) => {
    const id = req.params.id

    const item = await db.get(id)

    if (item) {
      ir.send(item.command)
      res.sendStatus(200)
    } else {
      res.sendStatus(404)
    }
  })

  app.listen(3000, () => {
    console.log('Example app listening on port 3000!')
  })
})
