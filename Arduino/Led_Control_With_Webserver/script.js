// Automatic Bell Project | Aadeesh Jain

let bellOnButton = document.querySelector("#onButton");

let bellOffButton = document.querySelector("#offButton");

bellOnButton.addEventListener("click", () => {
  console.log("Bell is ON");
});

bellOffButton.addEventListener("click", () => {
  console.log("Bell is OFF");
});

function bellRing() {
  bellOnButton.click();
  setTimeout(() => {
    bellOffButton.click();
  }, 3000);
}
