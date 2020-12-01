const hexToRgb = (hex) => {
  // Expand shorthand form (e.g. "03F") to full form (e.g. "0033FF")
  const shorthandRegex = /^#?([a-f\d])([a-f\d])([a-f\d])$/i
  hex = hex.replace(shorthandRegex, function (m, r, g, b) {
    return r + r + g + g + b + b
  })

  const result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex)
  return result
    ? {
        r: parseInt(result[1], 16),
        g: parseInt(result[2], 16),
        b: parseInt(result[3], 16),
      }
    : null
}

const rgbToHex = (r, g, b) => {
  return "#" + ((1 << 24) + (r << 16) + (g << 8) + b).toString(16).slice(1)
}

const setColors = () => {
  let colors = {
    t1: hexToRgb(document.querySelector("#set-led-color-team1").value),
    t2: hexToRgb(document.querySelector("#set-led-color-team2").value),
    tm: hexToRgb(document.querySelector("#set-led-color-timer").value),
  }
  post("/setcolors", colors)
}

const setBrightness = (value) => {
  const brightness = { brightness: value }
  post("/setbrightness", brightness)
}

const getLedProperties = () => {
  get("/getledprops").then((result) => {
    // document.querySelector("#teste").innerHTML = result
    const jsonResult = JSON.parse(result)

    document.querySelector("#set-led-color-team1").value = rgbToHex(
      jsonResult.t1.r,
      jsonResult.t1.g,
      jsonResult.t1.b
    )
    document.querySelector("#set-led-color-team2").value = rgbToHex(
      jsonResult.t2.r,
      jsonResult.t2.g,
      jsonResult.t2.b
    )
    document.querySelector("#set-led-color-timer").value = rgbToHex(
      jsonResult.tm.r,
      jsonResult.tm.g,
      jsonResult.tm.b
    )

    const elementInputRange = document.querySelector("#set-brightness")
    elementInputRange.value = jsonResult.bright
    resizeInputRange(elementInputRange)
  })
}

const resizeInputRange = (e) => {
  const min = e.min
  const max = e.max
  let val = e.value
  e.style.backgroundSize = ((val - min) * 100) / (max - min) + "% 100%"
}

const beginColor = () => {
  document.querySelectorAll(".set-led-color").forEach((led) => {
    led.addEventListener("input", (e) => {
      setColors()
    })
  })

  const elementInputRange = document.querySelector("#set-brightness")
  elementInputRange.addEventListener("input", (e) => {
    resizeInputRange(e.target)
    setBrightness(e.target.value)
  })

  document.querySelector("#save").addEventListener("click", (e) => {
    e.preventDefault()
    get("/save")
      .then(() => {
        document.querySelector("#save-confirmation").innerHTML =
          "Configurações salvas!"
      })
      .then(() => {
        setTimeout(() => {
          document.querySelector("#save-confirmation").innerHTML = ""
        }, 3000)
      })
  })

  getLedProperties()
}
beginColor()
