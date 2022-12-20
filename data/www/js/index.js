const dynamicLoadHtmlContent = () => {
  const afterLoad = () => {
    document
      .querySelector("#menu-button")
      .addEventListener("click", toggleMobileMenu)
  }

  const htmlList = Array.from(
    document.querySelectorAll(`[class*='dynamic-load-']`)
  ).map((e) => e.className.replace("dynamic-load-", ""))
  dynamicLoadAllHtml(htmlList, afterLoad)
}

const documentReady = () => {
  dynamicLoadHtmlContent()
}

if (document.readyState !== "loading") {
  documentReady()
} else {
  document.addEventListener("DOMContentLoaded", documentReady)
}

document.querySelector("#start").addEventListener("click", (e) => {
  clearInterval(INTERVALO)
  INTERVALO = setInterval(() => {
    milissegundos()
  }, 10)
  if (document.querySelector("#team_a_score").textContent == '--') {
    changeValue('team_a_score', 0)
    changeValue('team_b_score', 0)
    changeDisabledButtons(true)
  }
})

function changeDisabledButtons(enable){
  document.querySelector("#stop").disabled = !enable
  document.querySelector("#pause").disabled = !enable
  document.querySelector("#add_team_a").disabled = !enable
  document.querySelector("#add_team_b").disabled = !enable
  document.querySelector("#sub_team_a").disabled = !enable
  document.querySelector("#sub_team_b").disabled = !enable
}

document.querySelector("#pause").addEventListener("click", (e) => {
  clearInterval(INTERVALO)
})

document.querySelector("#stop").addEventListener("click", (e) => {
  clearInterval(INTERVALO)
  resetCronometer()
  resetScoreboard()
  changeDisabledButtons(false)
})

function resetCronometer() {
  miliNum = 0
  segNum = 0
  minNum = 0
  horNum = 0
  miliseg.innerHTML = '00'
  seg.innerHTML = '00'
  min.innerHTML = '00'
  hor.innerHTML = '00'
}

function resetScoreboard() {
  changeValue('team_a_score', '--')
  changeValue('team_b_score', '--')
}

document.querySelector("#add_team_a").addEventListener("click", (e) => {
  newScore = updateScore("team_a_score", 1, true)
  post("/setscoreteama", { "score": newScore })
})

document.querySelector("#add_team_b").addEventListener("click", (e) => {
  updateScore('team_b_score', 1, false)
})

document.querySelector("#sub_team_a").addEventListener("click", (e) => {
  updateScore('team_a_score', -1, true)
  post("/setscoreteama", { "score": newScore})
})

document.querySelector("#sub_team_b").addEventListener("click", (e) => {
  updateScore('team_b_score', -1, false)
})

function changeValue(tagId, newValue) {
  document.querySelector(`#${tagId}`).textContent = newValue
}

function updateScore(tagId, newValue, isTeamA) {
  currentScore = parseInt(document.querySelector(`#${tagId}`).textContent)
  if (currentScore == 0 && newValue == -1) {
    return 0
  }

  newScore = currentScore += newValue
  changeValue(tagId, newScore)
  return newScore
}

const miliseg = document.querySelector('.milissegundos')
const seg = document.querySelector('.segundos')
const min = document.querySelector('.minutos')
const hor = document.querySelector('.horas')

let miliNum = 0
let segNum = 0
let minNum = 0
let horNum = 0
let INTERVALO

function milissegundos() {
  miliNum++
  if (miliNum < 10) {
    miliseg.innerHTML = '0' + miliNum
  } else {
    miliseg.innerHTML = miliNum
  }

  if (miliNum == 99) {
    miliNum = 0
    segundos()
  }
}

function segundos() {
  segNum++
  if (segNum < 10) {
    seg.innerHTML = '0' + segNum
  } else {
    seg.innerHTML = segNum
  }

  if (segNum == 59) {
    segNum = 0
    minutos()
  }
}

function minutos() {
  minNum++
  if (minNum < 10) {
    min.innerHTML = '0' + minNum
  } else {
    min.innerHTML = minNum
  }

  if (horNum == 59) {
    minNum = 0
    horas()
  }
}

function horas() {
  horNum++
  if (horNum < 10) {
    hor.innerHTML = '0' + horNum
  } else {
    hor.innerHTML = horNum
  }
}