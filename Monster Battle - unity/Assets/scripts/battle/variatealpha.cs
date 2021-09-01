using UnityEngine;
using System.Collections;

public class variatealpha : MonoBehaviour
{
	public float speed;
	public float min_alpha;
	public float max_alpha;

	private SpriteRenderer sr;
	private float alpha;
	private int direction = -1;

	void Start ()
	{
		sr = gameObject.GetComponent<SpriteRenderer> ();
		alpha = max_alpha;
		direction = -1;
	}

	void Update ()
	{
		if (direction == 1)
		{
			alpha += speed * Time.deltaTime;

			if (alpha > max_alpha)
			{
				alpha = max_alpha;
				direction = -1;
			}
		}

		else if (direction == -1)
		{
			alpha -= speed * Time.deltaTime;

			if (alpha < min_alpha)
			{
				alpha = min_alpha;
				direction = 1;
			}
		}

		Color c = sr.color;
		c.a = alpha;
		sr.color = c;
	}
}
