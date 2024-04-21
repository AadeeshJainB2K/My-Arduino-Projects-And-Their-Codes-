// Automatic Bell Project | Aadeesh Jain

let bellOnButton = document.querySelector("#onButton");

let bellOffButton = document.querySelector("#offButton");

bellOnButton.addEventListener("click", () => {
  console.log("bell is on ");
});

bellOffButton.addEventListener("click", () => {
  console.log("bell is off ");
});

function bellRing() {
  bellOnButton.click();
  setTimeout(() => {
    bellOffButton.click();
  }, 3000);
}
