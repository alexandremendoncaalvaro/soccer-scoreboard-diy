const hexToRgb = (hex) => {
  // Expand shorthand form (e.g. "03F") to full form (e.g. "0033FF")
  const shorthandRegex = /^#?([a-f\d])([a-f\d])([a-f\d])$/i;
  hex = hex.replace(shorthandRegex, function (m, r, g, b) {
    return r + r + g + g + b + b;
  });

  const result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
  return result
    ? {
        r: parseInt(result[1], 16),
        g: parseInt(result[2], 16),
        b: parseInt(result[3], 16),
      }
    : null;
};

const rgbToHex = (r, g, b) => {
  return "#" + ((1 << 24) + (r << 16) + (g << 8) + b).toString(16).slice(1);
};

const setColor = () => {
  let color = {
    t1: hexToRgb(document.querySelector("#set-led-color-team1").value),
    t2: hexToRgb(document.querySelector("#set-led-color-team2").value),
    tm: hexToRgb(document.querySelector("#set-led-color-timer").value),
  };
  post("/setcolor", color);
};

const setBrightness = (value) => {
  const brightness = { brightness: value };
  post("/setbrightness", brightness);
};

const getLed = () => {
  get("/getled").then((result) => {
    document.querySelector("#teste").innerHTML = result;
    const jsonResult = JSON.parse(result);
    document.querySelector("#set-brightness").value = jsonResult.bright;
    document.querySelector("#set-led-color-team1").value = rgbToHex(
      jsonResult.t1.r,
      jsonResult.t1.g,
      jsonResult.t1.b
    );
    document.querySelector("#set-led-color-team2").value = rgbToHex(
      jsonResult.t2.r,
      jsonResult.t2.g,
      jsonResult.t2.b
    );
    document.querySelector("#set-led-color-timer").value = rgbToHex(
      jsonResult.tm.r,
      jsonResult.tm.g,
      jsonResult.tm.b
    );
  });
};

const beginColor = () => {
  document.querySelectorAll(".set-led-color").forEach((led) => {
    led.addEventListener("input", (e) => {
      setColor();
    });
  });
  document.querySelector("#set-brightness").addEventListener("input", (e) => {
    const min = e.target.min,
      max = e.target.max,
      val = e.target.value;

    e.target.style.backgroundSize =
      ((val - min) * 100) / (max - min) + "% 100%";

    setBrightness(e.target.value);
  });

  getLed();
};
beginColor();
