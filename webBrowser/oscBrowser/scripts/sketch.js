let oscPort;
let server = {
	IP : "0.0.0.0",
	port : 9999
}
function setup() {
	oscPort = new osc.WebSocketPort({
		url: `ws://${server.IP}:${server.port}`, // URL to your Web Socket server.
		metadata: true
	});
	oscPort.on("ready", onOscReady);
	oscPort.on("close", onOscClose);
	oscPort.on("message", onMessage);
	oscPort.open();
}

function draw(){
	// send("/theAddress", floor(random(-10, 10)));
    // send("/other/address", random(-10, 10));
    // send("/yet/another/address", "text");
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
