
#include "voronoi.h"
#include <CGAL/draw_voronoi_diagram_2.h>
void graphFromBitboard(std::vector<ColoredPoint>& points, unsigned long long bitboard, int color) {
  unsigned long long anchor = 1ull << 63;
  for (int i = 0; i < 64; i++) {
    if (((anchor >> i) & bitboard) != 0) { // piece at this index, 0,0 is going to be the top left part of the board
      // a little weird but it's flipped black on the bottom white on the top
      int random_num = std::rand() % 10000;
      double scaler = 1000000;
      double noise = random_num/scaler;

      // adding a little bit of noise to avoid co-linearity
      points.emplace_back(i%8+ noise +0.5, std::floor(i/8)+ noise + 0.5, color);
    }
  }
}



std::map<int, double> computeVDColorArea(std::vector<ColoredPoint> & graph,double x1Bound, double y1Bound, double x2Bound, double y2Bound) {
  std::vector<Point_2> points;
  std::map<Point_2, int> colorMap;
  std::map<int,double> colorArea;
  for (auto i : graph) {
    Point_2 pt  = Point_2(i.x, i.y);
    colorMap[pt] = i.color;
    points.push_back(pt);
  }

  // construct delauny from points
  DT dt(points.begin(), points.end());
  dt.is_valid();

  //Wrap the triangulation with a Voronoi diagram to get voronoi faces
  VD vd(dt);
  // CGAL::draw(vd);
  const auto ConvertToSeg = [&](const CGAL::Object seg_obj, bool outgoing) -> Kernal::Segment_2 {
    //One of these will succeed and one will have a NULL pointer
    const Kernal::Segment_2 *dseg = CGAL::object_cast<Kernal::Segment_2>(&seg_obj);
    const Kernal::Ray_2     *dray = CGAL::object_cast<Kernal::Ray_2>(&seg_obj);
    if (dseg) { //Okay, we have a segment
      return *dseg;
    } else {    //Must be a ray
      const auto &source = dray->source();
      const auto dsx     = source.x();
      const auto dsy     = source.y();
      const auto &dir    = dray->direction();
      const auto tpoint  = Kernal::Point_2(dsx+RAY_LENGTH*dir.dx(),dsy+RAY_LENGTH*dir.dy());
      if(outgoing)
        return Kernal::Segment_2(
          dray->source(),
          tpoint
        );
      else
        return Kernal::Segment_2(
          tpoint,
          dray->source()
        );
    }
  };

  int fnum = 0;
  //iterate through all faces of voronoi
  for(VD::Face_iterator fit = vd.faces_begin(); fit!=vd.faces_end();++fit,fnum++){
    CGAL::Polygon_2<Kernal> pgon;

    VD::Face::Ccb_halfedge_circulator ec_start = fit->ccb();

    //Current location of the edge circulator
    VD::Face::Ccb_halfedge_circulator ec = ec_start;

    do {
      //The dual of the edge of Delaunay triangle is either a segment or a ray.
      // const CGAL::Object seg_dual = rt.dual(ec->dual());
      const CGAL::Object seg_dual = vd.dual().dual(ec->dual());

      //Convert the segment/ray into a segment
      const auto this_seg = ConvertToSeg(seg_dual, ec->has_target());

      pgon.push_back(this_seg.source());


      if(!ec->has_target()){
        const CGAL::Object nseg_dual = vd.dual().dual(ec->next()->dual());
        const auto next_seg = ConvertToSeg(nseg_dual, ec->next()->has_target());
        pgon.push_back(next_seg.target());
      }
    } while ( ++ec != ec_start ); //Loop until we get back to the beginning


    // Define bounding box polygon
    CGAL::Polygon_2<Kernal> bounding_box;
    bounding_box.push_back(Point_2(x1Bound, y1Bound));
    bounding_box.push_back(Point_2(x2Bound, y1Bound));
    bounding_box.push_back(Point_2(x2Bound, y2Bound));
    bounding_box.push_back(Point_2(x1Bound, y2Bound));

    std::list<CGAL::Polygon_with_holes_2<Kernal>> intersect;
    CGAL::intersection(pgon, bounding_box, std::back_inserter(intersect));

    //expect only one polygon
    auto &poly_w_holes = intersect.front();

    // gives the polygon w/o holes based on outer boundry
    auto &poly_outer   = poly_w_holes.outer_boundary();
    auto site = fit->dual()->point();
    colorArea[colorMap[site]] += CGAL::to_double(poly_outer.area());
  }
  return colorArea;
}

