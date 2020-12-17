# Easy OSC

## Web Browser

Drop index.html from oscBrowser forlder into your webBrowser. It use [osc.js](https://github.com/colinbdclark/osc.js) library, you can find it into library folder.



### How to use

#### Initialization + Read

```javascript
let oscPort;
let server = {
    ID : "127.0.0.1", // address of the Web Socket server.
    port : 6969       // port number the Web Socket server is listenning to.
};

function setup(){
	oscPort = new osc.WebSocketPort({
		url: `ws://${server.IP}:${server.port}`, 
		metadata: true
	});
	oscPort.on("ready", onOscReady);
	oscPort.on("close", onOscClose);
	oscPort.on("message", onMessage);
	oscPort.open();
}

function onOscReady(){
    console.log("You are connected to the web socket server");
}

function onOscClose(){
    console.log("You are disconnected");
}

function onMessage(oscMsg){
    console.log("An OSC message just arrived!");
    console.log(oscMsg.address);
    for(let arg of oscMsg.args){
        console.log(arg.value);
    }
}
```

#### Write

```javascript
function send(address, value){
    oscPort.send({
		address: address,
		args: [{
			type: getType(value),
			value: value
		}]
	});   
}

function getType(value){
    if(toString.call(value) === '[object Number]'){
        if((""+value).includes(".")){
            return "f";
        }else{
            return "i";
        }
    }
    else if(toString.call(value) === '[object String]'){
        return "s";
    }
}

function whatEver(){
    send("/theAddress", 123);
    send("/other/address", 123.4);
    send("/yet/another/address", "text");
}
```

### Exemple

#### Initialization

Setup *IP* *<u>Default</u> : 127.0.0.1*

Setup *PORT* for communication IN & OUT *<u>Default</u> : 6969*

Click *Connect*

#### Send :

You just have to setup html for sending data 

```html
<input type=ANY name=OSC.ADDRESS/>
```

```html
<li>
    <label for="title">Title : </label>
    <input id="title" type="text" name="/title"/>
</li>
<li>
    <label for="cube_x">Cube X : </label>
    <input id="cube_x" type="range" min="-5" max="5" step="0.1" name="/cube/x"/>
    <span></span><!-- if present, this span will automatically display the value of the input -->
</li>
```

#### Recieve :

Just implement this script into a new javascript file.

this is already present into scripts/sketch.js

```javascript
docReady(function(){
    oscPort.on("message", onMessage);    
});

function onMessage(oscMsg) {
    console.log("An OSC message just arrived!", oscMsg);
}
```
