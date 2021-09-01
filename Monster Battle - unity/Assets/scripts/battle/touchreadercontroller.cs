using UnityEngine;
using System.Collections;

public class touchreadercontroller : MonoBehaviour
{
	private battlecontroller battle_script;
	private PolygonCollider2D region_def1;
	private PolygonCollider2D region_neu1;
	private PolygonCollider2D region_atk1;
	private PolygonCollider2D region_def2;
	private PolygonCollider2D region_neu2;
	private PolygonCollider2D region_atk2;

	void Start ()
	{
		battle_script = GameObject.Find ("Battle Controller").GetComponent<battlecontroller> ();
		region_def1 = transform.GetChild (0).gameObject.GetComponent<PolygonCollider2D>();
		region_neu1 = transform.GetChild (1).gameObject.GetComponent<PolygonCollider2D>();
		region_atk1 = transform.GetChild (2).gameObject.GetComponent<PolygonCollider2D>();
		region_def2 = transform.GetChild (3).gameObject.GetComponent<PolygonCollider2D>();
		region_neu2 = transform.GetChild (4).gameObject.GetComponent<PolygonCollider2D>();
		region_atk2 = transform.GetChild (5).gameObject.GetComponent<PolygonCollider2D>();
	}

	void Update ()
	{
		//Usa o touch
		if (Input.touchCount > 0)
		{
			foreach (Touch touch in Input.touches)
			{
				Vector3 world_point = Camera.main.ScreenToWorldPoint (touch.position);
				CheckRegions (world_point);
			}
		} 

		//Alternativamente pode usar o mouse tmb
		else if (Input.GetMouseButton (0))
		{
			Vector3 world_point = Camera.main.ScreenToWorldPoint (Input.mousePosition);
			CheckRegions (world_point);
		}
	}

	void CheckRegions(Vector3 world_point)
	{
		if (region_def1.OverlapPoint(world_point))
			battle_script.SetFieldPosition (1, FieldPosition.POSITION_DEFENSIVE);
		else if (region_neu1.OverlapPoint(world_point))
			battle_script.SetFieldPosition (1, FieldPosition.POSITION_NEUTRAL);
		else if (region_atk1.OverlapPoint(world_point))
			battle_script.SetFieldPosition (1, FieldPosition.POSITION_OFFENSIVE);

		else if (region_def2.OverlapPoint(world_point))
			battle_script.SetFieldPosition (2, FieldPosition.POSITION_DEFENSIVE);
		else if (region_neu2.OverlapPoint(world_point))
			battle_script.SetFieldPosition (2, FieldPosition.POSITION_NEUTRAL);
		else if (region_atk2.OverlapPoint(world_point))
			battle_script.SetFieldPosition (2, FieldPosition.POSITION_OFFENSIVE);
	}
}
