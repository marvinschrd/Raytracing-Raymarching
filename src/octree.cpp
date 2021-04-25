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

	/*float width = (octree_aabb_.extent()*2).Magnitude() / sqrt(3);
	float parent_width = octree_aabb_.extent().x * 2;*/
	float child_width = octree_aabb_.extent().x;

	maths::AABB3 first_aabb(maths::Vector3f(
		octree_aabb_.bottom_left().x, octree_aabb_.bottom_left().y + child_width, octree_aabb_.bottom_left().z),
		maths::Vector3f(octree_aabb_.center().x + child_width, octree_aabb_.center().y, octree_aabb_.center().z));
	 Octree firstoctant(max_spheres_number_, max_depth_, first_aabb, depth_ + 1);

	maths::AABB3 second_aabb(maths::Vector3f(
		octree_aabb_.center().x, octree_aabb_.center().y + child_width, octree_aabb_.center().z + child_width),
		maths::Vector3f(octree_aabb_.top_right().x + child_width, octree_aabb_.top_right().y, octree_aabb_.top_right().z+ child_width));
	Octree secondoctant(max_spheres_number_, max_depth_, second_aabb, depth_ + 1);
		
	maths::AABB3 third_aabb(octree_aabb_.bottom_left(), octree_aabb_.center());
	Octree thirdoctant(max_spheres_number_, max_depth_, third_aabb, depth_ + 1);

	maths::AABB3 fourth_aabb(maths::Vector3f(
		octree_aabb_.bottom_left().x + child_width, octree_aabb_.bottom_left().y, octree_aabb_.bottom_left().z),
		maths::Vector3f(octree_aabb_.center().x + child_width, octree_aabb_.center().y, octree_aabb_.center().z));
	Octree fourthoctant(max_spheres_number_, max_depth_, fourth_aabb, depth_ + 1);

	maths::AABB3 fifth_aabb(maths::Vector3f(
		octree_aabb_.center().x - child_width, octree_aabb_.center().y + child_width, octree_aabb_.center().z),
		maths::Vector3f(octree_aabb_.top_right().x - child_width, octree_aabb_.top_right().y, octree_aabb_.top_right().z));
	Octree fifthoctant(max_spheres_number_, max_depth_, fifth_aabb, depth_ + 1);

	maths::AABB3 sixth_aabb(octree_aabb_.center(),octree_aabb_.top_right());
	Octree sixthtoctant(max_spheres_number_, max_depth_, sixth_aabb, depth_ + 1);

	maths::AABB3 seventh_aabb(maths::Vector3f(
		octree_aabb_.bottom_left().x, octree_aabb_.bottom_left().y, octree_aabb_.bottom_left().z - child_width),
		maths::Vector3f(octree_aabb_.center().x, octree_aabb_.center().y, octree_aabb_.center().z- child_width));
	Octree seventhoctant(max_spheres_number_, max_depth_, seventh_aabb, depth_ + 1);

	maths::AABB3 eight_aabb(maths::Vector3f(
		octree_aabb_.center().x, octree_aabb_.center().y - child_width, octree_aabb_.center().z),
		maths::Vector3f(octree_aabb_.top_right().x, octree_aabb_.top_right().y - child_width, octree_aabb_.top_right().z));
	Octree eightoctant(max_spheres_number_, max_depth_, eight_aabb, depth_ + 1);

	childs_.resize(8);
	childs_ = { firstoctant,secondoctant,thirdoctant,fourthoctant,fifthoctant,sixthtoctant,seventhoctant,eightoctant };
	
	for (Octree child : childs_)
	{
		for(int i = 0; i < spheres_.size(); ++i)
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
				std::vector<maths::Sphere> childs_spheres;
				childs_spheres = child.Retrieve_spheres(ray);

				for (maths::Sphere sphere : childs_spheres)
				{
					spheres_to_check.push_back(sphere);
				}
			}
		}
	}
	return spheres_to_check;
}
