/* eslint-env browser, es6, jquery */
function request (dest, options = {}) {
  return new Promise((resolve, reject) => {
    let req = new XMLHttpRequest()
    req.onload = function (e) {
      resolve(options.json ? JSON.parse(req.responseText) : req.responseText)
    }
    req.open(options.method || 'GET', dest)
    req.send()
  })
}

function sleep (ms) {
  return new Promise(resolve => setTimeout(resolve, ms))
}

async function createList () {
  const list = await request('/list', { json: true })
  let element = $('#list')

  element.empty()

  for (let x of list) {
    let div = $(`<div class="list-group-item list-group-item-action d-flex align-items-start"></div>`)
    let link = $(`<a class="flex-grow-1"> ${x.name || x._id} </a>`)
    let button = $(`<button style="font-size:.5em;" type="button" class="btn btn-sm btn-danger"><i class="fas fa-trash-alt fa-lg"></i></button>`)

    div.append(link).append(button)

    link.click(async () => {
      div.addClass('active')
      await request(`/send/${x._id}`)
      div.removeClass('active')
    })

    button.click(async () => {
      div.addClass('active')
      await request(`/list/${x._id}`, { method: 'DELETE' })
      div.removeClass('active')
      createList()
    })

    element.append(div)
  }
}

createList()

$('#learn-button').click(async () => {
  const name = $('#learn-text').val()
  const res = await request(`/learn?name=${name}`, { json: true })

  while (true) {
    let success = await request(`/list/${res.id}`)

    await sleep(400)

    if (success.trim() !== '') {
      break
    }
  }

  createList()
})
