import './App.css';
import ModelViewer from 'react-model-viewer';

const modelPath = 'https://raw.githubusercontent.com/mylinhvu11/finalproj-spatialkeyframing/main/animate/src/assets/static-3d-assets/gtlf/sonic/scene.gltf';

function App() {
  return (
    <div style={{padding: "10%"}}>
      <ModelViewer type="gtlf" src={modelPath} />
    </div>
  );
}

export default App;
