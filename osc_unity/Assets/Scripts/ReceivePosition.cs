using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ReceivePosition : MonoBehaviour {
    public OSC osc;

    void Start(){
        osc.SetAddressHandler("/cube/x", OnReceiveX);
        osc.SetAddressHandler("/cube/y", OnReceiveY);
        osc.SetAddressHandler("/cube/z", OnReceiveZ);
    }

    void OnReceiveX(OscMessage message)
    {
        Vector3 position = transform.position;
        position.x = message.GetFloat(0);
        transform.position = position;
    }

    void OnReceiveY(OscMessage message)
    {
        Vector3 position = transform.position;
        position.y = message.GetFloat(0);
        transform.position = position;
    }

    void OnReceiveZ(OscMessage message)
    {
        Vector3 position = transform.position;
        position.z = message.GetFloat(0);
        transform.position = position;
    }

    private void Update()
    {
        if (Input.GetKeyUp(KeyCode.Space))
        {
            OscMessage msg = new OscMessage();
            msg.address = "/cursor";
            msg.values.Add(Input.mousePosition.x);
            msg.values.Add(Input.mousePosition.y);
            msg.values.Add(Input.mousePosition.z);
            osc.Send(msg);
        }
    }
}