using UnityEngine;
using System.Collections;

public class menucontroller : MonoBehaviour
{
	void Start ()
	{
		//Impede a tela do celular de suspender
		Screen.sleepTimeout = SleepTimeout.NeverSleep;
	}
}
