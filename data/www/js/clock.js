const showClock = () => {
  const clockElement = document.querySelector("#clock")
  clockElement.innerHTML = moment().format("DD/MM/YYYY HH:mm:ss")
}

const setClock = () => {
  const clock = {
    datetime: moment().format("DD/MM/YYYY HH:mm:ss"),
  }
  post("/setclock", clock)
    .then(() => {
      document.querySelector("#clock-confirmation").innerHTML = "Sincronizado!"
    })
    .then(() => {
      setTimeout(() => {
        document.querySelector("#clock-confirmation").innerHTML = ""
      }, 3000)
    })
}

const beginClock = () => {
  showClock()
  window.setInterval(showClock, 900)
  document.querySelector("#set-clock").addEventListener("click", (e) => {
    e.preventDefault()
    setClock()
  })
}
beginClock()
