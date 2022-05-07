const dynamicLoadHtml = (personalizedAttribute) => {
  return new Promise((resolve, reject) => {
    const path = `./${personalizedAttribute}.html`
    const ajax = new XMLHttpRequest()
    ajax.open("GET", path, true)
    ajax.send()
    ajax.onload = (e) => {
      const htmlPlace = document.querySelector(
        `.dynamic-load-${personalizedAttribute}`
      )
      htmlPlace.outerHTML = ajax.responseText
      resolve()
    }
  })
}

const dynamicLoadAllHtml = (personalizedAttributes, callback) => {
  const allHtml = personalizedAttributes.map(dynamicLoadHtml)
  Promise.all(allHtml).then(callback)
}
