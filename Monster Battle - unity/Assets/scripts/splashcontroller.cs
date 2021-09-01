using UnityEngine;
using System.Collections;

public class splashcontroller : MonoBehaviour
{
	public changescene fadeScript;
	public string nextScene;
	public float seconds_in_splash;
	private float passed_time;

	void Start ()
	{
		passed_time = 0.0f;
	}

	void Update () 
	{
		passed_time += Time.deltaTime;

		if (passed_time >= seconds_in_splash)
		{
			fadeScript.ChangeScene (nextScene);
			gameObject.SetActive (false);
		}
	}
}
