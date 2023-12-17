using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class playAudio : MonoBehaviour
{
    // Start is called before the first frame update
    public GameObject audioSource;
    

    void Start()
    {

    }
    // Update is called once per frame
    void Update()
    {
        
    }

  void OnTriggerEnter(Collider col) {
audioSource.SetActive(true);
}
 
void OnTriggerExit(Collider col) {
  audioSource.SetActive(false);
}
}
