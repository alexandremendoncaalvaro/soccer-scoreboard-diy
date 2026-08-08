const dynamicLoadHtml = (personalizedAttribute) => {
  return new Promise((resolve, reject) => {
    const path = `./${personalizedAttribute}.html`
    const ajax = new XMLHttpRequest()
    ajax.open("GET", path, true)
    ajax.send()
    ajax.onload = (e) => {
      if (ajax.status !== 200) {
        reject(new Error(`Falha ao carregar ${path}: status ${ajax.status}`))
        return
      }
      const htmlPlace = document.querySelector(
        `.dynamic-load-${personalizedAttribute}`
      )
      htmlPlace.outerHTML = ajax.responseText
      resolve()
    }

    ajax.onerror = () => reject(new Error(`Erro de rede ao carregar ${path}`))
  })
}

const dynamicLoadAllHtml = (personalizedAttributes, callback) => {
  const allHtml = personalizedAttributes.map(dynamicLoadHtml)
  Promise.all(allHtml).then(callback)
}
