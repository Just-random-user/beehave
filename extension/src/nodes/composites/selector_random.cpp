/**************************************************************************/
/*  selector_random.cpp                                                   */
/**************************************************************************/
/*                         This file is part of:                          */
/*                               BEEHAVE                                  */
/*                      https://bitbra.in/beehave                         */
/**************************************************************************/
/* Copyright (c) 2024-present Beehave Contributors.                       */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "selector_random.h"

using namespace godot;

SelectorRandomComposite::SelectorRandomComposite() {

}

SelectorRandomComposite::~SelectorRandomComposite() {

}

void SelectorRandomComposite::_bind_methods() {

}


TypedArray<int> _get_indexes_reversed() {
    TypedArray<int> reversed;
    for (i = 0; i < _children_bag.size(); ++i)
        reversed.push_back(i);
    reversed.reverse();
    return reversed;
}

void _reset() {
    TypedArray<Node> new_order = get_shuffled_children(); // TODO: implement randomized_composite
    _children_bag = new_order.duplicate();
    _children_bag.reverse();
}

BeehaveTickStatus SelectorRandomComposite::tick(Ref<BeehaveContext> context) {
    if (_children_bag.is_empty())
        _reset();

    for (i = 0; i < _get_indexes_reversed(); ++i) {
        BeehaveTreeNode *child = _children_bag[i];
        BeehaveTickStatus response = child->tick(context);
        switch response {
            case SUCCESS:
                _children_bag.erase(child);
                return SUCCESS;
            case FAILURE:
                _children_bag.erase(child);
                break;
            case RUNNING:
                return RUNNING;
        }
    }
    return FAILURE;
}


