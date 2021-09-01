using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.Collections;

public class changescene : MonoBehaviour
{
	enum ChangeStates
	{
		FADE_IN,
		DO_NOTHING,
		FADE_OUT,
		LEAVE_SCENE
	};

	private Image fade_image;
	private ChangeStates state;
	private string next_scene_name;
	private float alpha;

	public float fadein_speed = 2.5f;
	public float fadeout_speed = 2.5f;

	void Start()
	{
		fade_image = transform.GetChild (0).gameObject.GetComponent<Image> ();
		fade_image.gameObject.SetActive (true);
		state = ChangeStates.FADE_IN;
		alpha = 1.0f;
	}

	void Update()
	{
		if (state == ChangeStates.FADE_IN)
		{
			alpha -= fadein_speed * Time.deltaTime;
			AdjustAlpha (alpha);

			if (alpha <= 0.0f)
			{	
				alpha = 0.0f;
				state = ChangeStates.DO_NOTHING;
				fade_image.gameObject.SetActive (false);
			}
		} 

		else if (state == ChangeStates.FADE_OUT)
		{
			alpha += fadeout_speed * Time.deltaTime;
			AdjustAlpha (alpha);

			if (alpha >= 1.0f)
			{
				alpha = 1.0f;
				state = ChangeStates.LEAVE_SCENE;
			}
		}

		else if (state == ChangeStates.LEAVE_SCENE)
		{
			SceneManager.LoadScene (next_scene_name);
		}
	}

	private void AdjustAlpha(float alpha)
	{
		Color c = fade_image.color;
		c.a = alpha;
		fade_image.color = c;
	}

	public void ChangeScene(string sceneName)
	{
		next_scene_name = sceneName;
		state = ChangeStates.FADE_OUT;
		fade_image.gameObject.SetActive (true);
	}
}
