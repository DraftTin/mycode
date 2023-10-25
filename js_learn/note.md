# JavaScript Note

## Asynchronous
```javascript
setTimeout(myFunc, 3000)
or setTimeout(function(args) {...}, 3000)
or setTimeout(() => {...}, 3000)
```
In the example above, myFunc is used as a callback function. 

Modern javascript programmes usually use Promise instead of callbacks because the latter is hard to write and difficult to debug.

### Callback hell
```javascript
asyncOperation1((result1) => {
  // 第一个异步操作完成
  asyncOperation2(result1, (result2) => {
    // 第二个异步操作完成
    asyncOperation3(result2, (result3) => {
      // 第三个异步操作完成
      // ...
    });
  });
});
```
Code nesting, poor readability and maintainability.

## Promise
| myPromise.state | myPromise.result |  |
| ------------ | -----------|-------------------|
| pending | undefined | unresolved and unrejected yet |
| fulfilled | a result value | resolved |
| rejected | an error object | error |
1. **Support Chain call**: more readable and maintainable.
2. **Error Catch**: errors will be passed down alongside the chain until encountering the first catch method.
```javascript
asyncOperation1()
  .then((result1) => {
    // 第一个异步操作完成
    return asyncOperation2(result1);
  })
  .then((result2) => {
    // 第二个异步操作完成
    return asyncOperation3(result2);
  })
  .then((result3) => {
    // 第三个异步操作完成
    // ...
  })
  .catch((error) => {
    // 错误处理
    console.error(error);
  });
/////////////////////////////
// 2 ways to handle error
asyncOperation()
  .then((result) => {
    console.log(result); 
  }, (error) => {
    console.error(error);
  })
  .catch((error) => {
    console.error(error)
  });
// or 
asyncOperation()
  .then((result) => {
    console.log(result); // 不会执行，因为Promise被拒绝
  })
  .catch((error) => {
    console.error(error)
  });
```

## Async/Await

The keyword **async** before a function makes the function return a promise.
```javascript
async function myFunction() {
  return "Hello";
}
// ==
function myFunction() {
  return Promise.resolve("Hello");
}
```

The **await** keyword can only be used inside an async function. 

The **await** keyword makes the function pause the execution and wait for a resolved promise before it continues

## Prototype Chain

Prototypes are the mechanism by which JavaScript objects inherit features from one another. In this article, we explain what a prototype is, how prototype chain works, and how a prototype for an object can be set.