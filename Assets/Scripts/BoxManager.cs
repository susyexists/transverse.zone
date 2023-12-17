using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;
using Newtonsoft.Json;

public class BoxManager : MonoBehaviour
{
    SerialPort serial = new SerialPort("COM9",115200);
    public bool leftButton;
    public bool rightButton;
    public bool topButton;
    public bool bottomButton;
    public bool joySwitch;
    public bool toggleSwitch;
    public float joyX;
    public float joyY;



    void Start()
    {
        serial.Open();    
    }

    void Update()
    {
        try{
        string serialData = serial.ReadLine();
        dynamic data  = JsonConvert.DeserializeObject(serialData);
        leftButton = data.leftButton;
        rightButton = data.rightButton;
        topButton = data.topButton;
        bottomButton = data.bottomButton;
        joySwitch = data.joySwitch;
        toggleSwitch = data.toggle;
        joyX = data.joyX;
        joyY = data.joyY;
        }
        catch{
            throw;
        }

    }


}
