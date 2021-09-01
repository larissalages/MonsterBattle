using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class TouchController : MonoBehaviour
{
	public PolygonCollider2D region1;
	public PolygonCollider2D region2;
	public PolygonCollider2D region3;

	public Text textnumtouches;
	public Text texttouchregion1;
	public Text texttouchregion2;
	public Text texttouchregion3;

	private bool istouching1;
	private bool istouching2;
	private bool istouching3;

	void Update ()
	{
		textnumtouches.text = "Number of Detected Touches: " + Input.touchCount.ToString ();

		istouching1 = false;
		istouching2 = false;
		istouching3 = false;

		//Usa o touch
		if (Input.touchCount > 0)
		{
			foreach (Touch touch in Input.touches)
			{
				Vector3 world_point = Camera.main.ScreenToWorldPoint (touch.position);
				CheckRegions (world_point);
			}
		} 

		//Alternativamente pode usar o mouse também
		else if (Input.GetMouseButton (0))
		{
			Vector3 world_point = Camera.main.ScreenToWorldPoint (Input.mousePosition);
			CheckRegions (world_point);
		}

		texttouchregion1.text = "Touch Region 1: " + istouching1.ToString ();
		texttouchregion2.text = "Touch Region 2: " + istouching2.ToString ();
		texttouchregion3.text = "Touch Region 3: " + istouching3.ToString ();
	}

	void CheckRegions(Vector3 world_point)
	{
		istouching1 = istouching1 || region1.OverlapPoint (world_point);
		istouching2 = istouching2 || region2.OverlapPoint (world_point);
		istouching3 = istouching3 || region3.OverlapPoint (world_point);
	}
}
