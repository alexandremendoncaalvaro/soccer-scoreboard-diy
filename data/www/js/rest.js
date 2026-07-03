const post = (url, data) => {
  return new Promise((resolve, reject) => {
    const ajax = new XMLHttpRequest()

    ajax.open("POST", url, true)
    ajax.setRequestHeader("Content-type", "application/x-www-form-urlencoded")

    ajax.send(JSON.stringify(data))

    ajax.onreadystatechange = () => {
      if (ajax.readyState == 4) {
        if (ajax.status == 200) {
          resolve(ajax.responseText)
        } else {
          reject(new Error(`POST ${url} falhou com status ${ajax.status}`))
        }
      }
    }

    ajax.onerror = () => reject(new Error(`POST ${url} erro de rede`))
  })
}

const get = (url) => {
  return new Promise((resolve, reject) => {
    const ajax = new XMLHttpRequest()

    ajax.open("GET", url, true)

    ajax.send()

    ajax.onreadystatechange = () => {
      if (ajax.readyState == 4) {
        if (ajax.status == 200) {
          const data = ajax.responseText
          resolve(data)
        } else {
          reject(new Error(`GET ${url} falhou com status ${ajax.status}`))
        }
      }
    }

    ajax.onerror = () => reject(new Error(`GET ${url} erro de rede`))
  })
}
