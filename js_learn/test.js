async function myDisplay() {
  let myPromise = new Promise(function(resolve) {
    setTimeout(() => resolve("I love You !!"), 3000)
  });
  ii = await myPromise;
  console.log(ii)
}

myDisplay();