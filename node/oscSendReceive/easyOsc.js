/*----------------------------------------*\
  receiver_osc - oscTools.js
  @author Evrard Vincent (vincent@ogre.be)
  @Date:   2023-10-05 13:19:01
  @Last Modified time: 2023-10-16 13:07:53
\*----------------------------------------*/

const osc = require("osc");
const _ = require("./validator.js");


module.exports = class EasyOsc{
    constructor(outIP = "192.168.4.1", inPort = 9999, outPort = 8888){
        this.IN_PORT = inPort;
        this.OUT_PORT = outPort;
        this.OUT_IP = outIP;
        this.messageHandler = ()=>{}
        this.readyHandler = ()=>{}
        this.udpPort = new osc.UDPPort({
            localAddress: "0.0.0.0",
            localPort: this.IN_PORT,
            metadata: true
        });
        this.udpPort.on("message", (oscMsg, timeTag, info) => {
            if(this.messageHandler(oscMsg, timeTag, info) === false){
                return;
            }
            const action = oscMsg.address.substr(1);
            if(this[action] && typeof this[action] === "function"){
                this[action](oscMsg, timeTag, info, ...oscMsg.args);
            }
        });
        this.udpPort.on("ready", () => {
            this.readyHandler();
        });
    }
    onMessage(handler){
        if(!handler || typeof handler !== "function") return;
        this.messageHandler = handler;
    }
    onReady(handler){
        if(!handler || typeof handler !== "function") return;
        this.readyHandler = handler;
    }
    begin(){
        this.udpPort.open();
    }
    send(address, ...values) {
        this.udpPort.send({
            address : address,
            args : values.map(value => toOscData(value))
        }, this.OUT_IP, this.OUT_PORT);

    }
};

const toOscData = (value)=>{
    if(_.isInteger(value)){
        return {
            type: "i",
            value: value
        }
    }
    else if(_.isFloat(value)){
        return {
            type: "f",
            value: value
        }
    }
    else if(_.isString(value)){
        return {
            type: "s",
            value: value
        }
    }
}
