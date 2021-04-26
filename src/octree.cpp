#include "octree.h"

void Octree::Insert(const maths::Sphere& sphere)
{
		if (spheres_.size() >= max_spheres_number_ && depth_ < max_depth_ && !has_split_)
		{
			std::cout << "first aabb childs number = " << childs_.size() << "\n";
			std::cout << " firt aabb center = " << octree_aabb_.center().x << ", " << octree_aabb_.center().y << ", " << octree_aabb_.center().z << "\n";
			Split();
			std::cout << "first aabb childs number = " << childs_.size() << "\n";
		}
		if(has_split_)
		{
			bool inserted_sphere = false;
			for (int i = 0; i< childs_.size(); ++i)
			{
				//std::cout << " childs_ size = " << childs_.size() << "\n";
				std::cout << "child aabb center = " << childs_[i].aabb().center().x << "," << childs_[i].aabb().center().y << "," << childs_[i].aabb().center().z << "\n";
				if(maths::AABBContainSphere(sphere,childs_[i].aabb()))
				{
					childs_[i].Insert(sphere);
					inserted_sphere = true;
				}
				//std::cout << "childs spheres_size = " << child.spheres_.size() << "\n";
			}
			
			// means that the sphere could not be contained in any of the childs
			// so it is added into this aabb and not the childs
			if(!inserted_sphere) 
			{
				spheres_.push_back(sphere);
				std::cout << "couldn't fit sphere \n";
			}
		}
		else
		{
			spheres_.push_back(sphere);
			std::cout << "added sphere \n";
		}
}

void Octree::Split()
{
	has_split_ = true;

	std::cout << "split \n";

	/*float child_width = (octree_aabb_.extent()).Magnitude() / sqrt(3);
	float parent_width = octree_aabb_.extent().x * 2;*/
	float child_width = octree_aabb_.extent().x/2;

	/*maths::AABB3 first_aabb(maths::Vector3f(
		octree_aabb_.bottom_left().x, octree_aabb_.bottom_left().y + child_width, octree_aabb_.bottom_left().z),
		maths::Vector3f(octree_aabb_.center().x, octree_aabb_.center().y + child_width, octree_aabb_.center().z));*/
	maths::AABB3 first_aabb(maths::Vector3f(octree_aabb_.center().x - child_width, octree_aabb_.center().y, octree_aabb_.center().z + child_width),
		maths::Vector3f(octree_aabb_.center().x, octree_aabb_.center().y + child_width, octree_aabb_.center().z));
	 Octree firstoctant(max_spheres_number_, max_depth_, first_aabb, depth_ + 1);

	/*maths::AABB3 second_aabb(maths::Vector3f(
		octree_aabb_.center().x, octree_aabb_.center().y, octree_aabb_.center().z + child_width),
		maths::Vector3f(octree_aabb_.top_right().x, octree_aabb_.top_right().y, octree_aabb_.top_right().z + child_width));*/
	 maths::AABB3 second_aabb(maths::Vector3f(octree_aabb_.center().x, octree_aabb_.center().y, octree_aabb_.center().z + child_width),
		 maths::Vector3f(octree_aabb_.center().x + child_width, octree_aabb_.center().y + child_width, octree_aabb_.center().z));
	Octree secondoctant(max_spheres_number_, max_depth_, second_aabb, depth_ + 1);
		
	maths::AABB3 third_aabb(octree_aabb_.bottom_left(), octree_aabb_.center());
	Octree thirdoctant(max_spheres_number_, max_depth_, third_aabb, depth_ + 1);

	/*maths::AABB3 fourth_aabb(maths::Vector3f(
		octree_aabb_.bottom_left().x + child_width, octree_aabb_.bottom_left().y, octree_aabb_.bottom_left().z),
		maths::Vector3f(octree_aabb_.center().x + child_width, octree_aabb_.center().y, octree_aabb_.center().z));*/
	maths::AABB3 fourth_aabb(maths::Vector3f(octree_aabb_.center().x, octree_aabb_.center().y - child_width, octree_aabb_.center().z + child_width),
		maths::Vector3f(octree_aabb_.center().x + child_width, octree_aabb_.center().y, octree_aabb_.center().z));
	Octree fourthoctant(max_spheres_number_, max_depth_, fourth_aabb, depth_ + 1);

	/*maths::AABB3 fifth_aabb(maths::Vector3f(
		octree_aabb_.center().x - child_width, octree_aabb_.center().y + child_width, octree_aabb_.center().z),
		maths::Vector3f(octree_aabb_.top_right().x - child_width, octree_aabb_.top_right().y, octree_aabb_.top_right().z));*/
	maths::AABB3 fifth_aabb(maths::Vector3f(octree_aabb_.center().x - child_width, octree_aabb_.center().y, octree_aabb_.center().z),
		maths::Vector3f(octree_aabb_.center().x, octree_aabb_.center().y + child_width, octree_aabb_.center().z - child_width));
	Octree fifthoctant(max_spheres_number_, max_depth_, fifth_aabb, depth_ + 1);

	maths::AABB3 sixth_aabb(octree_aabb_.center(),octree_aabb_.top_right());
	Octree sixthtoctant(max_spheres_number_, max_depth_, sixth_aabb, depth_ + 1);

	/*maths::AABB3 seventh_aabb(maths::Vector3f(
		octree_aabb_.bottom_left().x, octree_aabb_.bottom_left().y, octree_aabb_.bottom_left().z - child_width),
		maths::Vector3f(octree_aabb_.center().x, octree_aabb_.center().y, octree_aabb_.center().z- child_width));*/
	maths::AABB3 seventh_aabb(maths::Vector3f(octree_aabb_.center().x - child_width, octree_aabb_.center().y - child_width, octree_aabb_.center().z),
		maths::Vector3f(octree_aabb_.center().x, octree_aabb_.center().y, octree_aabb_.center().z - child_width));
	Octree seventhoctant(max_spheres_number_, max_depth_, seventh_aabb, depth_ + 1);

	/*maths::AABB3 eight_aabb(maths::Vector3f(
		octree_aabb_.center().x, octree_aabb_.center().y - child_width, octree_aabb_.center().z),
		maths::Vector3f(octree_aabb_.top_right().x, octree_aabb_.top_right().y - child_width, octree_aabb_.top_right().z));*/
	maths::AABB3 eight_aabb(maths::Vector3f(octree_aabb_.center().x, octree_aabb_.center().y - child_width, octree_aabb_.center().z - child_width),
		maths::Vector3f(octree_aabb_.center().x + child_width, octree_aabb_.center().y, octree_aabb_.center().z - child_width));
	Octree eightoctant(max_spheres_number_, max_depth_, eight_aabb, depth_ + 1);

	childs_.resize(8);
	childs_ = { firstoctant,secondoctant,thirdoctant,fourthoctant,fifthoctant,sixthtoctant,seventhoctant,eightoctant };
	
	for (Octree child : childs_)
	{
		for(int i = 0; i < spheres_.size(); ++i)
		{
			if(AABBContainSphere(spheres_[i],child.aabb()))
			{
				std::cout << "erased \n";
				child.Insert(spheres_[i]);
				spheres_.erase(spheres_.begin()+i);
			}
		}
	}
	//std::cout << spheres_.size() << "\n";
}

std::vector<maths::Sphere> Octree::Retrieve_spheres(maths::Ray3 ray)
{
//	auto begin = std::chrono::high_resolution_clock::now();
	std::vector<maths::Sphere> spheres_to_check;
	spheres_to_check.reserve(1);
	
	if(ray.IntersectAABB3(octree_aabb_))
	{
		for (maths::Sphere sphere : spheres_)
		{
			if(spheres_to_check.size() == spheres_to_check.capacity())
			{
				spheres_to_check.reserve(spheres_to_check.size() * 2);
			}
			spheres_to_check.emplace_back(sphere);
		}
		if(has_split_)
		{
			for (Octree child : childs_)
			{
				std::vector<maths::Sphere> childs_spheres;
				childs_spheres.reserve(1);
				childs_spheres = child.Retrieve_spheres(ray);

				for (maths::Sphere sphere : childs_spheres)
				{
					if(spheres_to_check.size() == spheres_to_check.capacity())
					{
						spheres_to_check.reserve(spheres_to_check.size() * 2);
					}
					spheres_to_check.emplace_back(sphere);
				}
			}
		}
	}
	/*auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	std::cout << " retrieving duration : " << duration.count() << " microsecondes " << "\n";*/
	return spheres_to_check;
}

void Octree::Retrieve_2(maths::Ray3 ray, std::vector<maths::Sphere>& spheres_to_check)
{
	if(ray.IntersectAABB3(octree_aabb_))
	{
		for (maths::Sphere sphere : spheres_)
		{
			if (spheres_to_check.size() == spheres_to_check.capacity())
			{
				spheres_to_check.reserve(spheres_to_check.size() * 2);
			}
			spheres_to_check.emplace_back(sphere);
		}
		if(has_split())
		{
			for (Octree child : childs_)
			{
				child.Retrieve_2(ray, spheres_to_check);
			}
		}
	}

	
}

//std::string Octree::ToString()
//{
//	/*std::string s;
//	for (int i = 0; i < depth_; i++)
//		s += "-";
//
//		s += "Node [" + octree_aabb_.bottom_left().ToString() + ", " + topRight.ToString() + ", contains " + std::to_string(child.size);
//
//	for (int i = 0; i < shpere.size(); i++)
//		s += "Sphere[" + i + "] at " + sphere[i].position.ToString();
//
//	for (int i = 0; i < child.size; i++)
//		s += child[i].ToString();
//	
//	return s;*/
//}
