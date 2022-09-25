#pragma once

#include <memory>
#include <vector>
#include "entitycell.h"

class entity : public entityCell
{
public:
    entity() {}
    void add(std::shared_ptr<entityCell> cellPointer);
    bool hit(const ray& ray, double minT, double maxT, hitRecord& result) const override;

private:
    std::vector<std::shared_ptr<entityCell>> m_cells;
};

void entity::add(std::shared_ptr<entityCell> cellPointer)
{
    m_cells.push_back(cellPointer);
};

bool entity::hit(const ray& ray, double minT, double maxT, hitRecord& result) const
{
    double minHitTime = maxT;
    hitRecord tempRecord;
    bool hited = false;

    for (auto cell : m_cells){
        if(cell->hit(ray, minT, minHitTime, tempRecord)){
            minHitTime = tempRecord.t;
            hited = true;
        }
    }
    result = tempRecord;
    return hited;
}