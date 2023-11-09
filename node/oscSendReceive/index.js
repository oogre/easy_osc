const EasyOsc = require("./easyOsc.js");
let flag = 1;

const osc = new EasyOsc("192.168.4.1", 9999, 8888);


osc.onMessage(({address, args:[{value}]})=>{
    console.log(address, ":", value);
});

osc.onReady(()=>{
    setInterval(()=>{
        osc.send("/touch", 13);    
    }, 500);
});


osc.begin();

