using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class optionscontroller : MonoBehaviour
{
	public changescene fadeScript;
	public soundcontroller soundScript;
	public Slider BGM_slider;
	public Slider SFX_slider;

	void Start()
	{
		//Impede a tela do celular de suspender
		Screen.sleepTimeout = SleepTimeout.NeverSleep;

		//Posiciona os sliders nos valores corretos
		BGM_slider.value = PlayerPrefs.GetFloat ("BGM_volume", 0.5f);
		SFX_slider.value = PlayerPrefs.GetFloat ("SFX_volume", 0.5f);
	}

	void Update ()
	{
		//Se apertar botão de voltar salva e vai pra o menu
		if (Input.GetKeyDown (KeyCode.Escape))
		{
			soundScript.SaveVolumeConfiguration ();
			fadeScript.ChangeScene ("menu3");
		}
	}
}
