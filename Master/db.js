const Datastore = require('nedb')

class DB {
  constructor (options) {
    this.db = new Datastore(options)
  }

  insert (item) {
    this.db.insert(item)
  }

  get (id) {
    return new Promise((resolve, reject) => {
      this.db.findOne({ _id: id }, (err, docs) => {
        if (err) return reject(err)

        resolve(docs)
      })
    })
  }

  delete (id) {
    return new Promise((resolve, reject) => {
      this.db.remove({ _id: id }, {}, (err, num) => {
        if (err) return reject(err)

        resolve(num)
      })
    })
  }

  list () {
    return new Promise((resolve, reject) => {
      this.db.find({}, (err, docs) => {
        if (err) return reject(err)

        resolve(docs)
      })
    })
  }
}

module.exports = DB
