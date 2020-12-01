const post = (url, data) => {
  return new Promise((resolve, reject) => {
    const ajax = new XMLHttpRequest()

    ajax.open("POST", url, true)
    ajax.setRequestHeader("Content-type", "application/x-www-form-urlencoded")

    ajax.send(JSON.stringify(data))

    ajax.onreadystatechange = () => {
      if (ajax.readyState == 4 && ajax.status == 200) {
        const data = ajax.responseText

        console.log(data)
        resolve(data)
      }
    }
  })
}

const get = (url) => {
  return new Promise((resolve, reject) => {
    const ajax = new XMLHttpRequest()

    ajax.open("GET", url, true)
    ajax.setRequestHeader("Content-type", "application/x-www-form-urlencoded")

    ajax.send()

    ajax.onreadystatechange = () => {
      if (ajax.readyState == 4 && ajax.status == 200) {
        data = ajax.responseText

        console.log(data)
        resolve(data)
      }
    }
  })
}
