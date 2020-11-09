const hexToRgb = (hex) => {
  // Expand shorthand form (e.g. "03F") to full form (e.g. "0033FF")
  var shorthandRegex = /^#?([a-f\d])([a-f\d])([a-f\d])$/i;
  hex = hex.replace(shorthandRegex, function (m, r, g, b) {
    return r + r + g + g + b + b;
  });

  var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
  return result
    ? {
        r: parseInt(result[1], 16),
        g: parseInt(result[2], 16),
        b: parseInt(result[3], 16),
      }
    : null;
};

const setColor = (colorHex) => {
  const color = hexToRgb(colorHex);
  post("/setcolor", color);
};

const setBrightness = (value) => {
  const brightness = { brightness: value };
  post("/setbrightness", brightness);
};

const beginColor = () => {
  document.querySelector("#set-led-color").addEventListener("input", (e) => {
    setColor(e.target.value);
  });

  document.querySelector("#set-brightness").addEventListener("input", (e) => {
    const min = e.target.min,
      max = e.target.max,
      val = e.target.value;

    e.target.style.backgroundSize =
      ((val - min) * 100) / (max - min) + "% 100%";
      
    setBrightness(e.target.value);
  });
};
beginColor();
