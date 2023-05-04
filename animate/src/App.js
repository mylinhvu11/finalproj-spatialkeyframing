import './App.css';
import ModelViewer from 'react-model-viewer';
import scene from "./assets/scene.gltf";

const modelPath = '/Users/armaangoel/Desktop/184/finalproj-spatialkeyframing/animate/src/assets/scene.gltf';

function App() {
  return (
    <div style={{padding: "10%"}}>
      <ModelViewer type="gtlf" src={scene} />
    </div>
  );
}

export default App;
