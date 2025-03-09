package a05.e2;

public interface Logic {

    abstract class Entity {
        private Position position;

        public Entity(Position position) {
            this.position = position;
        }

        public Position position() {
            return position;
        }
        
        public void move(Position position) {
            this.position = whereToGo(position);
        }

        protected abstract Position whereToGo(Position position);
    }

    boolean click(Position p);

    Entity getPlayer();

    Entity getEnemy();

    boolean isOver();
}
