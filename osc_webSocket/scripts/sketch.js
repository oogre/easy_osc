let oscPort;
let connected = false;

function docReady(fn) {
    // see if DOM is already available
    if (document.readyState === "complete" || document.readyState === "interactive") {
        // call on next available tick
        setTimeout(fn, 1);
    } else {
        document.addEventListener("DOMContentLoaded", fn);
    }
}

function setup() {
	const controlInputs = [...document.querySelectorAll("#controllers input")];
	for(const input of controlInputs){
		removeValue(input);
		disable(input);
	}
	document.querySelector("#configuration form").addEventListener("submit", onConfiguration, false);
}

function onConfiguration(event){
	event.preventDefault();
	if(!connected){
		const server = {};
		const configInputs = [...document.querySelectorAll("#configuration input:not([type=submit])")];
		for(const input of configInputs){
			server[input.name] = input.value;
		}
		oscPort = new osc.WebSocketPort({
			url: `ws://${server.IP}:${server.port}`, // URL to your Web Socket server.
			metadata: true
		});
		oscPort.on("ready", onOscRead);
		oscPort.on("close", onOscClose);
		oscPort.on("message", onMessage);
		oscPort.open();
	}
	else{
		oscPort.close();
	}
	
	return false;
}

function onMessage(oscMsg) {
	console.log("An OSC message just arrived!", oscMsg);
}

function onOscRead(){
	connected = true;
	document.querySelector("#configuration input[type=submit]").value = "Disconnect";
	const configInputs = [...document.querySelectorAll("#configuration input:not([type=submit])")];
	for(const input of configInputs){
		disable(input);
	}
	const controlInputs = [...document.querySelectorAll("#controllers input")];
	for(const input of controlInputs){
		displayValue(input);
		attachEvent(input);
		enable(input);
	}
}

function onOscClose(){
	connected = false;
	document.querySelector("#configuration input[type=submit]").value = "Connect";
	const configInputs = [...document.querySelectorAll("#configuration input:not([type=submit])")];
	for(const input of configInputs){
		enable(input);
	}
	const controlInputs = [...document.querySelectorAll("#controllers input")];
	for(const input of controlInputs){
		removeValue(input);
		detachEvent(input);
		disable(input);
	}
}

function disable(target){
	target.setAttribute("disabled", true);
}

function enable(target){
	target.removeAttribute("disabled");
}

function attachEvent(input){
	input.addEventListener("input", onInput, false);
}

function detachEvent(input){
	input.removeEventListener("input", onInput, false);
}

function onInput(event){
	if(!oscPort)return;
	displayValue(event.target);
	oscPort.send({
		address: event.target.name,
		args: [
			{
				type: getType(event.target),
				value: event.target.value
			}
		]
	});
}

function getType(target){
	switch(target.type){
		case "range" :  return "f";
		case "text" :   return "s";
	}
}

function displayValue(target){
	if(target.nextElementSibling){
		target.nextElementSibling.innerText = target.value;	
	}
}

function removeValue(target){
	if(target.nextElementSibling){
		target.nextElementSibling.innerText = "";	
	}
}

docReady(setup);