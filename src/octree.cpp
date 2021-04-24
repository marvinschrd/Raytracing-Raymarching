#include "octree.h"

void Octree::Insert(const maths::Sphere& sphere)
{
		if (spheres_.size() >= max_spheres_number_ && depth_ < max_depth_ && !has_split_)
		{
			Split();
		}
		if(has_split_)
		{
			bool inserted_sphere = false;
			for (Octree child : childs_)
			{
				if(maths::AABBContainSphere(sphere,child.aabb()))
				{
					child.Insert(sphere);
					inserted_sphere = true;
				}
			}
			
			// means that the sphere could not be contained in any of the childs
			// so it is added into this aabb and not the childs
			if(!inserted_sphere) 
			{
				spheres_.push_back(sphere);
			}
		}
		else
		{
			spheres_.push_back(sphere);
		}
}

void Octree::Split()
{
	has_split_ = true;

	/*float child_width = octree_aabb_.

	octree firstoctant;
	octree secondoctant;
	octree thirdoctant;
	octree fourthoctant;
	octree fifthoctant;
	octree sixthtoctant;
	octree seventhtoctant;
	octree eigthoctant;

	childs_ = {firstoctant,secondoctant,thirdoctant,fourthoctant,fifthoctant,sixthtoctant,seventhtoctant,eigthoctant};*/

	for (Octree child : childs_)
	{
		for(int i = 0; i <= spheres_.size(); ++i)
		{
			if(AABBContainSphere(spheres_[i],child.aabb()))
			{
				child.Insert(spheres_[i]);
				spheres_.erase(spheres_.begin()+i);
			}
		}
	}
}

std::vector<maths::Sphere> Octree::Retrieve_spheres(maths::Ray3 ray)
{
	std::vector<maths::Sphere> spheres_to_check;
	
	if(ray.IntersectAABB3(octree_aabb_))
	{
		for (maths::Sphere sphere : spheres_)
		{
			spheres_to_check.push_back(sphere);
		}
		if(has_split_)
		{
			for (Octree child : childs_)
			{
				child.Retrieve_spheres(ray);
			}
		}
	}
	return spheres_to_check;
}
